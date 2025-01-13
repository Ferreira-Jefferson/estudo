// components/RestoreProgress.js

import ProgressBar from "../ProgressBar";

export default function RestoreProgress({ progress }) {
  return (
    <div>
      <h2 className="text-xl font-bold text-red-900 mb-4">
        Restaurando...
      </h2>
      <ProgressBar progress={progress} />
    </div>
  );
}
